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
typedef  int /*<<< orphan*/  const zend_uchar ;
typedef  int /*<<< orphan*/  PHP_SHA1_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  PHP_SHA1Final (int /*<<< orphan*/  const* const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PHP_SHA1Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PHP_SHA1Update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t const) ; 
 int SCRAMBLE_LENGTH ; 
 int SHA1_MAX_LENGTH ; 
 int /*<<< orphan*/  php_mysqlnd_crypt (int /*<<< orphan*/  const* const,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

void php_mysqlnd_scramble(zend_uchar * const buffer, const zend_uchar * const scramble, const zend_uchar * const password, const size_t password_len)
{
	PHP_SHA1_CTX context;
	zend_uchar sha1[SHA1_MAX_LENGTH];
	zend_uchar sha2[SHA1_MAX_LENGTH];

	/* Phase 1: hash password */
	PHP_SHA1Init(&context);
	PHP_SHA1Update(&context, password, password_len);
	PHP_SHA1Final(sha1, &context);

	/* Phase 2: hash sha1 */
	PHP_SHA1Init(&context);
	PHP_SHA1Update(&context, (zend_uchar*)sha1, SHA1_MAX_LENGTH);
	PHP_SHA1Final(sha2, &context);

	/* Phase 3: hash scramble + sha2 */
	PHP_SHA1Init(&context);
	PHP_SHA1Update(&context, scramble, SCRAMBLE_LENGTH);
	PHP_SHA1Update(&context, (zend_uchar*)sha2, SHA1_MAX_LENGTH);
	PHP_SHA1Final(buffer, &context);

	/* let's crypt buffer now */
	php_mysqlnd_crypt(buffer, (const zend_uchar *)buffer, (const zend_uchar *)sha1, SHA1_MAX_LENGTH);
}