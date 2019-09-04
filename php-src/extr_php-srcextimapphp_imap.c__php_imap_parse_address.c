#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_4__ {scalar_t__ host; scalar_t__ mailbox; scalar_t__ adl; scalar_t__ personal; struct TYPE_4__* next; } ;
typedef  TYPE_1__ ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/ * _php_rfc822_write_address (TYPE_1__*) ; 
 int /*<<< orphan*/  add_next_index_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_property_string (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  object_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_string* _php_imap_parse_address (ADDRESS *addresslist, zval *paddress)
{
	zend_string *fulladdress;
	ADDRESS *addresstmp;
	zval tmpvals;

	addresstmp = addresslist;

	fulladdress = _php_rfc822_write_address(addresstmp);

	addresstmp = addresslist;
	do {
		object_init(&tmpvals);
		if (addresstmp->personal) add_property_string(&tmpvals, "personal", addresstmp->personal);
		if (addresstmp->adl) add_property_string(&tmpvals, "adl", addresstmp->adl);
		if (addresstmp->mailbox) add_property_string(&tmpvals, "mailbox", addresstmp->mailbox);
		if (addresstmp->host) add_property_string(&tmpvals, "host", addresstmp->host);
		add_next_index_object(paddress, &tmpvals);
	} while ((addresstmp = addresstmp->next));
	return fulladdress;
}