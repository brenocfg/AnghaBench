#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32 ;
struct cdb {int loop; int hslots; int hpos; int khash; int kpos; int dlen; int dpos; } ;

/* Variables and functions */
 int cdb_hash (char*,unsigned int) ; 
 int cdb_match (struct cdb*,char*,unsigned int,int) ; 
 int cdb_read (struct cdb*,char*,int,int) ; 
 int /*<<< orphan*/  uint32_unpack (char*,int*) ; 

int cdb_findnext(struct cdb *c, char *key, unsigned int len)
{
	char buf[8];
	uint32 pos;
	uint32 u;

	if (!c->loop) {
		u = cdb_hash(key, len);
		if (cdb_read(c, buf, 8, (u << 3) & 2047) == -1)
			return -1;
		uint32_unpack(buf + 4,&c->hslots);
		if (!c->hslots)
			return 0;
		uint32_unpack(buf, &c->hpos);
		c->khash = u;
		u >>= 8;
		u %= c->hslots;
		u <<= 3;
		c->kpos = c->hpos + u;
	}

	while (c->loop < c->hslots) {
		if (cdb_read(c, buf, 8, c->kpos) == -1)
			return -1;
		uint32_unpack(buf + 4, &pos);
		if (!pos)
			return 0;
		c->loop += 1;
		c->kpos += 8;
		if (c->kpos == c->hpos + (c->hslots << 3))
			c->kpos = c->hpos;
		uint32_unpack(buf, &u);
		if (u == c->khash) {
			if (cdb_read(c, buf, 8, pos) == -1)
				return -1;
			uint32_unpack(buf, &u);
			if (u == len)
			switch(cdb_match(c, key, len, pos + 8)) {
			case -1:
				return -1;
			case 1:
				uint32_unpack(buf + 4, &c->dlen);
				c->dpos = pos + 8 + len;
				return 1;
			}
		}
	}

	return 0;
}