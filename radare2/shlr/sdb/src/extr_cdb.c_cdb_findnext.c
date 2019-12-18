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
typedef  int ut32 ;
struct cdb {int fd; int hslots; int loop; int hpos; int size; int khash; int kpos; int dpos; int /*<<< orphan*/  dlen; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int KVLSZ ; 
 int /*<<< orphan*/  cdb_getkvlen (struct cdb*,int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cdb_read (struct cdb*,char*,int const,int) ; 
 int match (struct cdb*,char const*,int,int) ; 
 int /*<<< orphan*/  ut32_unpack (char*,int*) ; 

int cdb_findnext(struct cdb *c, ut32 u, const char *key, ut32 len) {
	char buf[8];
	ut32 pos;
	int m;
	len++;
	if (c->fd == -1) {
		return -1;
	}
	c->hslots = 0;
	if (!c->loop) {
		const int bufsz = ((u + 1) & 0xFF) ? sizeof (buf) : sizeof (buf) / 2;
		if (!cdb_read (c, buf, bufsz, (u << 2) & 1023)) {
			return -1;
		}
		/* hslots = (hpos_next - hpos) / 8 */
		ut32_unpack (buf, &c->hpos);
		if (bufsz == sizeof (buf)) {
			ut32_unpack (buf + 4, &pos);
		} else {
			pos = c->size;
		}
		if (pos < c->hpos) {
			return -1;
		}
		c->hslots = (pos - c->hpos) / (2 * sizeof (ut32));
		if (!c->hslots) {
			return 0;
		}
		c->khash = u;
		u = ((u >> 8) % c->hslots) << 3;
		c->kpos = c->hpos + u;
	}
	while (c->loop < c->hslots) {
		if (!cdb_read (c, buf, sizeof (buf), c->kpos)) {
			return 0;
		}
		ut32_unpack (buf + 4, &pos);
		if (!pos) {
			return 0;
		}
		c->loop++;
		c->kpos += sizeof (buf);
		if (c->kpos == c->hpos + (c->hslots << 3)) {
			c->kpos = c->hpos;
		}
		ut32_unpack (buf, &u);
		if (u == c->khash) {
			if (!cdb_getkvlen (c, &u, &c->dlen, pos) || !u) {
				return -1;
			}
			if (u == len) {
				if ((m = match (c, key, len, pos + KVLSZ)) == -1) {
					return 0;
				}
				if (m == 1) {
					c->dpos = pos + KVLSZ + len;
					return 1;
				}
			}
		}
	}
	return 0;
}