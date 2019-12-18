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
typedef  int /*<<< orphan*/  u8 ;
struct ts_kmp {unsigned int pattern_len; int /*<<< orphan*/ * pattern; scalar_t__ prefix_tbl; } ;
struct ts_config {int flags; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ts_config*) ; 
 int TS_IGNORECASE ; 
 struct ts_config* alloc_ts_config (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compute_prefix_tbl (void const*,unsigned int,scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,unsigned int) ; 
 int /*<<< orphan*/  toupper (int /*<<< orphan*/ ) ; 
 struct ts_kmp* ts_config_priv (struct ts_config*) ; 

__attribute__((used)) static struct ts_config *kmp_init(const void *pattern, unsigned int len,
				  gfp_t gfp_mask, int flags)
{
	struct ts_config *conf;
	struct ts_kmp *kmp;
	int i;
	unsigned int prefix_tbl_len = len * sizeof(unsigned int);
	size_t priv_size = sizeof(*kmp) + len + prefix_tbl_len;

	conf = alloc_ts_config(priv_size, gfp_mask);
	if (IS_ERR(conf))
		return conf;

	conf->flags = flags;
	kmp = ts_config_priv(conf);
	kmp->pattern_len = len;
	compute_prefix_tbl(pattern, len, kmp->prefix_tbl, flags);
	kmp->pattern = (u8 *) kmp->prefix_tbl + prefix_tbl_len;
	if (flags & TS_IGNORECASE)
		for (i = 0; i < len; i++)
			kmp->pattern[i] = toupper(((u8 *)pattern)[i]);
	else
		memcpy(kmp->pattern, pattern, len);

	return conf;
}