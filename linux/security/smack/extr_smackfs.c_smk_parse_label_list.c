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
struct smack_known_list_elem {int /*<<< orphan*/  list; struct smack_known* smk_label; } ;
struct smack_known {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct smack_known*) ; 
 int PTR_ERR (struct smack_known*) ; 
 struct smack_known_list_elem* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 struct smack_known* smk_import_entry (char*,int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int smk_parse_label_list(char *data, struct list_head *list)
{
	char *tok;
	struct smack_known *skp;
	struct smack_known_list_elem *sklep;

	while ((tok = strsep(&data, " ")) != NULL) {
		if (!*tok)
			continue;

		skp = smk_import_entry(tok, 0);
		if (IS_ERR(skp))
			return PTR_ERR(skp);

		sklep = kzalloc(sizeof(*sklep), GFP_KERNEL);
		if (sklep == NULL)
			return -ENOMEM;

		sklep->smk_label = skp;
		list_add(&sklep->list, list);
	}

	return 0;
}