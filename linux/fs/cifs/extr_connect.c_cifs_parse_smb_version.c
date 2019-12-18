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
struct smb_vol {int /*<<< orphan*/ * vals; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int MAX_OPT_ARGS ; 
#define  Smb_1 135 
#define  Smb_20 134 
#define  Smb_21 133 
#define  Smb_30 132 
#define  Smb_302 131 
#define  Smb_311 130 
#define  Smb_3any 129 
#define  Smb_default 128 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  cifs_smb_version_tokens ; 
 int /*<<< orphan*/  disable_legacy_dialects ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smb1_operations ; 
 int /*<<< orphan*/  smb1_values ; 
 int /*<<< orphan*/  smb20_operations ; 
 int /*<<< orphan*/  smb20_values ; 
 int /*<<< orphan*/  smb21_operations ; 
 int /*<<< orphan*/  smb21_values ; 
 int /*<<< orphan*/  smb302_values ; 
 int /*<<< orphan*/  smb30_operations ; 
 int /*<<< orphan*/  smb30_values ; 
 int /*<<< orphan*/  smb311_operations ; 
 int /*<<< orphan*/  smb311_values ; 
 int /*<<< orphan*/  smb3any_values ; 
 int /*<<< orphan*/  smbdefault_values ; 

__attribute__((used)) static int
cifs_parse_smb_version(char *value, struct smb_vol *vol, bool is_smb3)
{
	substring_t args[MAX_OPT_ARGS];

	switch (match_token(value, cifs_smb_version_tokens, args)) {
#ifdef CONFIG_CIFS_ALLOW_INSECURE_LEGACY
	case Smb_1:
		if (disable_legacy_dialects) {
			cifs_dbg(VFS, "mount with legacy dialect disabled\n");
			return 1;
		}
		if (is_smb3) {
			cifs_dbg(VFS, "vers=1.0 (cifs) not permitted when mounting with smb3\n");
			return 1;
		}
		vol->ops = &smb1_operations;
		vol->vals = &smb1_values;
		break;
	case Smb_20:
		if (disable_legacy_dialects) {
			cifs_dbg(VFS, "mount with legacy dialect disabled\n");
			return 1;
		}
		if (is_smb3) {
			cifs_dbg(VFS, "vers=2.0 not permitted when mounting with smb3\n");
			return 1;
		}
		vol->ops = &smb20_operations;
		vol->vals = &smb20_values;
		break;
#else
	case Smb_1:
		cifs_dbg(VFS, "vers=1.0 (cifs) mount not permitted when legacy dialects disabled\n");
		return 1;
	case Smb_20:
		cifs_dbg(VFS, "vers=2.0 mount not permitted when legacy dialects disabled\n");
		return 1;
#endif /* CIFS_ALLOW_INSECURE_LEGACY */
	case Smb_21:
		vol->ops = &smb21_operations;
		vol->vals = &smb21_values;
		break;
	case Smb_30:
		vol->ops = &smb30_operations;
		vol->vals = &smb30_values;
		break;
	case Smb_302:
		vol->ops = &smb30_operations; /* currently identical with 3.0 */
		vol->vals = &smb302_values;
		break;
	case Smb_311:
		vol->ops = &smb311_operations;
		vol->vals = &smb311_values;
		break;
	case Smb_3any:
		vol->ops = &smb30_operations; /* currently identical with 3.0 */
		vol->vals = &smb3any_values;
		break;
	case Smb_default:
		vol->ops = &smb30_operations; /* currently identical with 3.0 */
		vol->vals = &smbdefault_values;
		break;
	default:
		cifs_dbg(VFS, "Unknown vers= option specified: %s\n", value);
		return 1;
	}
	return 0;
}