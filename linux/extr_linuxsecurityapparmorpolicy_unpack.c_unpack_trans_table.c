#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char** table; int size; } ;
struct TYPE_3__ {TYPE_2__ trans; } ;
struct aa_profile {TYPE_1__ file; } ;
struct aa_ext {void* pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_ARRAYEND ; 
 int /*<<< orphan*/  AA_STRUCT ; 
 int /*<<< orphan*/  AA_STRUCTEND ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  aa_free_domain_entries (TYPE_2__*) ; 
 scalar_t__ isspace (char) ; 
 char** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int unpack_array (struct aa_ext*,int /*<<< orphan*/ *) ; 
 scalar_t__ unpack_nameX (struct aa_ext*,int /*<<< orphan*/ ,char*) ; 
 int unpack_strdup (struct aa_ext*,char**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool unpack_trans_table(struct aa_ext *e, struct aa_profile *profile)
{
	void *saved_pos = e->pos;

	/* exec table is optional */
	if (unpack_nameX(e, AA_STRUCT, "xtable")) {
		int i, size;

		size = unpack_array(e, NULL);
		/* currently 4 exec bits and entries 0-3 are reserved iupcx */
		if (size > 16 - 4)
			goto fail;
		profile->file.trans.table = kcalloc(size, sizeof(char *),
						    GFP_KERNEL);
		if (!profile->file.trans.table)
			goto fail;

		profile->file.trans.size = size;
		for (i = 0; i < size; i++) {
			char *str;
			int c, j, pos, size2 = unpack_strdup(e, &str, NULL);
			/* unpack_strdup verifies that the last character is
			 * null termination byte.
			 */
			if (!size2)
				goto fail;
			profile->file.trans.table[i] = str;
			/* verify that name doesn't start with space */
			if (isspace(*str))
				goto fail;

			/* count internal #  of internal \0 */
			for (c = j = 0; j < size2 - 1; j++) {
				if (!str[j]) {
					pos = j;
					c++;
				}
			}
			if (*str == ':') {
				/* first character after : must be valid */
				if (!str[1])
					goto fail;
				/* beginning with : requires an embedded \0,
				 * verify that exactly 1 internal \0 exists
				 * trailing \0 already verified by unpack_strdup
				 *
				 * convert \0 back to : for label_parse
				 */
				if (c == 1)
					str[pos] = ':';
				else if (c > 1)
					goto fail;
			} else if (c)
				/* fail - all other cases with embedded \0 */
				goto fail;
		}
		if (!unpack_nameX(e, AA_ARRAYEND, NULL))
			goto fail;
		if (!unpack_nameX(e, AA_STRUCTEND, NULL))
			goto fail;
	}
	return 1;

fail:
	aa_free_domain_entries(&profile->file.trans);
	e->pos = saved_pos;
	return 0;
}