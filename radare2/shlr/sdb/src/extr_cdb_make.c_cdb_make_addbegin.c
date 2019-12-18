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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut32 ;
struct cdb_make {int /*<<< orphan*/  b; } ;

/* Variables and functions */
 int KVLSZ ; 
 int buffer_putalign (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  pack_kvlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cdb_make_addbegin(struct cdb_make *c, ut32 keylen, ut32 datalen) {
	ut8 buf[KVLSZ];
	if (!pack_kvlen (buf, keylen, datalen)) {
		return 0;
	}
	return buffer_putalign (&c->b, (const char *)buf, KVLSZ);
}