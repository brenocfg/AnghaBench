#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut8 ;
typedef  scalar_t__ ut64 ;
typedef  int /*<<< orphan*/  fs_lbuf ;
struct TYPE_3__ {int buflen; scalar_t__ bufoff; int bytelen; scalar_t__ byteoff; scalar_t__ byte; scalar_t__ name; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ RFSType ;

/* Variables and functions */
 int R_MIN (int,int) ; 
 TYPE_1__* fstypes ; 
 int /*<<< orphan*/  memcmp (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 char* strdup (scalar_t__) ; 

__attribute__((used)) static char *fsname(const ut8* buf, ut64 length) {
	ut8 fs_lbuf[1024];
	int i, j, len, ret = false;

	for (i = 0; fstypes[i].name; i++) {
		RFSType *f = &fstypes[i];

		len = R_MIN (f->buflen, sizeof (fs_lbuf));
		memset (fs_lbuf, 0, sizeof (fs_lbuf));
		if (f->bufoff + len > length) {
			break;
		}
		memcpy (fs_lbuf, buf + f->bufoff, len);
		if ((f->buflen > 0) && len >= f->buflen) {
			int min = R_MIN (f->buflen, sizeof (fs_lbuf));
			if (!memcmp (fs_lbuf, f->buf, min)) {
				ret = true;
				len = R_MIN (f->bytelen, sizeof (fs_lbuf));
				if (f->byteoff + len > length) {
					break;
				}
				memcpy (fs_lbuf, buf + f->byteoff, len);
				// for (j = 0; j < f->bytelen; j++) {
				for (j = 0; j < len; j++) {
					if (fs_lbuf[j] != f->byte) {
						ret = false;
						break;
					}
				}
				if (ret) {
					return strdup (f->name);
				}
			}
		}
	}
	return NULL;
}