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
struct nls_table {int (* uni2char ) (int /*<<< orphan*/ ,unsigned char*,int) ;int /*<<< orphan*/  charset; } ;
typedef  int /*<<< orphan*/  ntfschar ;
struct TYPE_3__ {int /*<<< orphan*/  sb; struct nls_table* nls_map; } ;
typedef  TYPE_1__ ntfs_volume ;

/* Variables and functions */
 int EILSEQ ; 
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int const NLS_MAX_CHARSET_SIZE ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  ntfs_error (int /*<<< orphan*/ ,char*,...) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned char*,int) ; 

int ntfs_ucstonls(const ntfs_volume *vol, const ntfschar *ins,
		const int ins_len, unsigned char **outs, int outs_len)
{
	struct nls_table *nls = vol->nls_map;
	unsigned char *ns;
	int i, o, ns_len, wc;

	/* We don't trust outside sources. */
	if (ins) {
		ns = *outs;
		ns_len = outs_len;
		if (ns && !ns_len) {
			wc = -ENAMETOOLONG;
			goto conversion_err;
		}
		if (!ns) {
			ns_len = ins_len * NLS_MAX_CHARSET_SIZE;
			ns = kmalloc(ns_len + 1, GFP_NOFS);
			if (!ns)
				goto mem_err_out;
		}
		for (i = o = 0; i < ins_len; i++) {
retry:			wc = nls->uni2char(le16_to_cpu(ins[i]), ns + o,
					ns_len - o);
			if (wc > 0) {
				o += wc;
				continue;
			} else if (!wc)
				break;
			else if (wc == -ENAMETOOLONG && ns != *outs) {
				unsigned char *tc;
				/* Grow in multiples of 64 bytes. */
				tc = kmalloc((ns_len + 64) &
						~63, GFP_NOFS);
				if (tc) {
					memcpy(tc, ns, ns_len);
					ns_len = ((ns_len + 64) & ~63) - 1;
					kfree(ns);
					ns = tc;
					goto retry;
				} /* No memory so goto conversion_error; */
			} /* wc < 0, real error. */
			goto conversion_err;
		}
		ns[o] = 0;
		*outs = ns;
		return o;
	} /* else (!ins) */
	ntfs_error(vol->sb, "Received NULL pointer.");
	return -EINVAL;
conversion_err:
	ntfs_error(vol->sb, "Unicode name contains characters that cannot be "
			"converted to character set %s.  You might want to "
			"try to use the mount option nls=utf8.", nls->charset);
	if (ns != *outs)
		kfree(ns);
	if (wc != -ENAMETOOLONG)
		wc = -EILSEQ;
	return wc;
mem_err_out:
	ntfs_error(vol->sb, "Failed to allocate name!");
	return -ENOMEM;
}