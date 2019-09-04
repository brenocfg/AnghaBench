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
struct aa_ext {int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int EPROTONOSUPPORT ; 
 scalar_t__ VERSION_GT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VERSION_LT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_iface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,struct aa_ext*,int) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 scalar_t__ unpack_str (struct aa_ext*,char const**,char*) ; 
 int /*<<< orphan*/  unpack_u32 (struct aa_ext*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v5 ; 
 int /*<<< orphan*/  v7 ; 

__attribute__((used)) static int verify_header(struct aa_ext *e, int required, const char **ns)
{
	int error = -EPROTONOSUPPORT;
	const char *name = NULL;
	*ns = NULL;

	/* get the interface version */
	if (!unpack_u32(e, &e->version, "version")) {
		if (required) {
			audit_iface(NULL, NULL, NULL, "invalid profile format",
				    e, error);
			return error;
		}
	}

	/* Check that the interface version is currently supported.
	 * if not specified use previous version
	 * Mask off everything that is not kernel abi version
	 */
	if (VERSION_LT(e->version, v5) || VERSION_GT(e->version, v7)) {
		audit_iface(NULL, NULL, NULL, "unsupported interface version",
			    e, error);
		return error;
	}

	/* read the namespace if present */
	if (unpack_str(e, &name, "namespace")) {
		if (*name == '\0') {
			audit_iface(NULL, NULL, NULL, "invalid namespace name",
				    e, error);
			return error;
		}
		if (*ns && strcmp(*ns, name))
			audit_iface(NULL, NULL, NULL, "invalid ns change", e,
				    error);
		else if (!*ns)
			*ns = name;
	}

	return 0;
}