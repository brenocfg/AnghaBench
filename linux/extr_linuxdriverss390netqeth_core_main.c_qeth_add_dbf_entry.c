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
struct qeth_dbf_entry {int /*<<< orphan*/  dbf_list; scalar_t__ dbf_info; int /*<<< orphan*/  dbf_name; } ;
struct qeth_card {scalar_t__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_NAME_LEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  debug_hex_ascii_view ; 
 scalar_t__ debug_register (char*,int,int,int) ; 
 scalar_t__ debug_register_view (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_unregister (scalar_t__) ; 
 struct qeth_dbf_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_dbf_list ; 
 int /*<<< orphan*/  qeth_dbf_list_mutex ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_add_dbf_entry(struct qeth_card *card, char *name)
{
	struct qeth_dbf_entry *new_entry;

	card->debug = debug_register(name, 2, 1, 8);
	if (!card->debug) {
		QETH_DBF_TEXT_(SETUP, 2, "%s", "qcdbf");
		goto err;
	}
	if (debug_register_view(card->debug, &debug_hex_ascii_view))
		goto err_dbg;
	new_entry = kzalloc(sizeof(struct qeth_dbf_entry), GFP_KERNEL);
	if (!new_entry)
		goto err_dbg;
	strncpy(new_entry->dbf_name, name, DBF_NAME_LEN);
	new_entry->dbf_info = card->debug;
	mutex_lock(&qeth_dbf_list_mutex);
	list_add(&new_entry->dbf_list, &qeth_dbf_list);
	mutex_unlock(&qeth_dbf_list_mutex);

	return 0;

err_dbg:
	debug_unregister(card->debug);
err:
	return -ENOMEM;
}