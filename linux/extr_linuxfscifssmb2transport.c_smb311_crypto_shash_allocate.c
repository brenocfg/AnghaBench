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
struct cifs_secmech {int /*<<< orphan*/  sdeschmacsha256; int /*<<< orphan*/  hmacsha256; int /*<<< orphan*/  sdesccmacaes; int /*<<< orphan*/  cmacaes; int /*<<< orphan*/  sdescsha512; int /*<<< orphan*/  sha512; } ;
struct TCP_Server_Info {struct cifs_secmech secmech; } ;

/* Variables and functions */
 int cifs_alloc_hash (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cifs_free_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
smb311_crypto_shash_allocate(struct TCP_Server_Info *server)
{
	struct cifs_secmech *p = &server->secmech;
	int rc = 0;

	rc = cifs_alloc_hash("hmac(sha256)",
			     &p->hmacsha256,
			     &p->sdeschmacsha256);
	if (rc)
		return rc;

	rc = cifs_alloc_hash("cmac(aes)", &p->cmacaes, &p->sdesccmacaes);
	if (rc)
		goto err;

	rc = cifs_alloc_hash("sha512", &p->sha512, &p->sdescsha512);
	if (rc)
		goto err;

	return 0;

err:
	cifs_free_hash(&p->cmacaes, &p->sdesccmacaes);
	cifs_free_hash(&p->hmacsha256, &p->sdeschmacsha256);
	return rc;
}