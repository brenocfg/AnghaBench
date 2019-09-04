#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * sdescsha512; int /*<<< orphan*/ * sdescmd5; int /*<<< orphan*/ * sdeschmacmd5; int /*<<< orphan*/ * sdeschmacsha256; int /*<<< orphan*/ * sdesccmacaes; int /*<<< orphan*/ * ccmaesdecrypt; int /*<<< orphan*/ * ccmaesencrypt; int /*<<< orphan*/ * hmacmd5; int /*<<< orphan*/ * sha512; int /*<<< orphan*/ * md5; int /*<<< orphan*/ * hmacsha256; int /*<<< orphan*/ * cmacaes; } ;
struct TCP_Server_Info {TYPE_1__ secmech; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_aead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_free_shash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void
cifs_crypto_secmech_release(struct TCP_Server_Info *server)
{
	if (server->secmech.cmacaes) {
		crypto_free_shash(server->secmech.cmacaes);
		server->secmech.cmacaes = NULL;
	}

	if (server->secmech.hmacsha256) {
		crypto_free_shash(server->secmech.hmacsha256);
		server->secmech.hmacsha256 = NULL;
	}

	if (server->secmech.md5) {
		crypto_free_shash(server->secmech.md5);
		server->secmech.md5 = NULL;
	}

	if (server->secmech.sha512) {
		crypto_free_shash(server->secmech.sha512);
		server->secmech.sha512 = NULL;
	}

	if (server->secmech.hmacmd5) {
		crypto_free_shash(server->secmech.hmacmd5);
		server->secmech.hmacmd5 = NULL;
	}

	if (server->secmech.ccmaesencrypt) {
		crypto_free_aead(server->secmech.ccmaesencrypt);
		server->secmech.ccmaesencrypt = NULL;
	}

	if (server->secmech.ccmaesdecrypt) {
		crypto_free_aead(server->secmech.ccmaesdecrypt);
		server->secmech.ccmaesdecrypt = NULL;
	}

	kfree(server->secmech.sdesccmacaes);
	server->secmech.sdesccmacaes = NULL;
	kfree(server->secmech.sdeschmacsha256);
	server->secmech.sdeschmacsha256 = NULL;
	kfree(server->secmech.sdeschmacmd5);
	server->secmech.sdeschmacmd5 = NULL;
	kfree(server->secmech.sdescmd5);
	server->secmech.sdescmd5 = NULL;
	kfree(server->secmech.sdescsha512);
	server->secmech.sdescsha512 = NULL;
}