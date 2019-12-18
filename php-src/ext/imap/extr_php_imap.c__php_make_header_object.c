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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_3__ {char* remail; char* subject; char* in_reply_to; char* message_id; char* newsgroups; char* followup_to; char* references; scalar_t__ return_path; scalar_t__ sender; scalar_t__ reply_to; scalar_t__ bcc; scalar_t__ cc; scalar_t__ from; scalar_t__ to; scalar_t__ date; } ;
typedef  TYPE_1__ ENVELOPE ;

/* Variables and functions */
 int /*<<< orphan*/ * _php_imap_parse_address (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_assoc_object (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_property_str (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_property_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  object_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _php_make_header_object(zval *myzvalue, ENVELOPE *en)
{
	zval paddress;
	zend_string *fulladdress=NULL;

	object_init(myzvalue);

	if (en->remail) add_property_string(myzvalue, "remail", en->remail);
	if (en->date) add_property_string(myzvalue, "date", (char*)en->date);
	if (en->date) add_property_string(myzvalue, "Date", (char*)en->date);
	if (en->subject) add_property_string(myzvalue, "subject", en->subject);
	if (en->subject) add_property_string(myzvalue, "Subject", en->subject);
	if (en->in_reply_to) add_property_string(myzvalue, "in_reply_to", en->in_reply_to);
	if (en->message_id) add_property_string(myzvalue, "message_id", en->message_id);
	if (en->newsgroups) add_property_string(myzvalue, "newsgroups", en->newsgroups);
	if (en->followup_to) add_property_string(myzvalue, "followup_to", en->followup_to);
	if (en->references) add_property_string(myzvalue, "references", en->references);

	if (en->to) {
		array_init(&paddress);
		fulladdress = _php_imap_parse_address(en->to, &paddress);
		if (fulladdress) {
			add_property_str(myzvalue, "toaddress", fulladdress);
		}
		add_assoc_object(myzvalue, "to", &paddress);
	}

	if (en->from) {
		array_init(&paddress);
		fulladdress = _php_imap_parse_address(en->from, &paddress);
		if (fulladdress) {
			add_property_str(myzvalue, "fromaddress", fulladdress);
		}
		add_assoc_object(myzvalue, "from", &paddress);
	}

	if (en->cc) {
		array_init(&paddress);
		fulladdress = _php_imap_parse_address(en->cc, &paddress);
		if (fulladdress) {
			add_property_str(myzvalue, "ccaddress", fulladdress);
		}
		add_assoc_object(myzvalue, "cc", &paddress);
	}

	if (en->bcc) {
		array_init(&paddress);
		fulladdress = _php_imap_parse_address(en->bcc, &paddress);
		if (fulladdress) {
			add_property_str(myzvalue, "bccaddress", fulladdress);
		}
		add_assoc_object(myzvalue, "bcc", &paddress);
	}

	if (en->reply_to) {
		array_init(&paddress);
		fulladdress = _php_imap_parse_address(en->reply_to, &paddress);
		if (fulladdress) {
			add_property_str(myzvalue, "reply_toaddress", fulladdress);
		}
		add_assoc_object(myzvalue, "reply_to", &paddress);
	}

	if (en->sender) {
		array_init(&paddress);
		fulladdress = _php_imap_parse_address(en->sender, &paddress);
		if (fulladdress) {
			add_property_str(myzvalue, "senderaddress", fulladdress);
		}
		add_assoc_object(myzvalue, "sender", &paddress);
	}

	if (en->return_path) {
		array_init(&paddress);
		fulladdress = _php_imap_parse_address(en->return_path, &paddress);
		if (fulladdress) {
			add_property_str(myzvalue, "return_pathaddress", fulladdress);
		}
		add_assoc_object(myzvalue, "return_path", &paddress);
	}
}