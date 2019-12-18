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
typedef  int /*<<< orphan*/  substring_t ;
struct smb_vol {int direct_io; int strict_io; int cache_ro; int cache_rw; } ;

/* Variables and functions */
 int MAX_OPT_ARGS ; 
#define  Opt_cache_loose 132 
#define  Opt_cache_none 131 
#define  Opt_cache_ro 130 
#define  Opt_cache_rw 129 
#define  Opt_cache_strict 128 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_cacheflavor_tokens ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cifs_parse_cache_flavor(char *value, struct smb_vol *vol)
{
	substring_t args[MAX_OPT_ARGS];

	switch (match_token(value, cifs_cacheflavor_tokens, args)) {
	case Opt_cache_loose:
		vol->direct_io = false;
		vol->strict_io = false;
		vol->cache_ro = false;
		vol->cache_rw = false;
		break;
	case Opt_cache_strict:
		vol->direct_io = false;
		vol->strict_io = true;
		vol->cache_ro = false;
		vol->cache_rw = false;
		break;
	case Opt_cache_none:
		vol->direct_io = true;
		vol->strict_io = false;
		vol->cache_ro = false;
		vol->cache_rw = false;
		break;
	case Opt_cache_ro:
		vol->direct_io = false;
		vol->strict_io = false;
		vol->cache_ro = true;
		vol->cache_rw = false;
		break;
	case Opt_cache_rw:
		vol->direct_io = false;
		vol->strict_io = false;
		vol->cache_ro = false;
		vol->cache_rw = true;
		break;
	default:
		cifs_dbg(VFS, "bad cache= option: %s\n", value);
		return 1;
	}
	return 0;
}