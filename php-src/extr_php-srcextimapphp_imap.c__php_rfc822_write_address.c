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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  ADDRESS ;

/* Variables and functions */
 int SENDBUFLEN ; 
 int _php_imap_address_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfc822_write_address (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/ * zend_string_init (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_throw_error (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static zend_string* _php_rfc822_write_address(ADDRESS *addresslist)
{
	char address[SENDBUFLEN];

	if (_php_imap_address_size(addresslist) >= SENDBUFLEN) {
		zend_throw_error(NULL, "Address buffer overflow");
		return NULL;
	}
	address[0] = 0;
	rfc822_write_address(address, addresslist);
	return zend_string_init(address, strlen(address), 0);
}