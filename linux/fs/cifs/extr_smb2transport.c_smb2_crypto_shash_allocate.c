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
struct TYPE_2__ {int /*<<< orphan*/  sdeschmacsha256; int /*<<< orphan*/  hmacsha256; } ;
struct TCP_Server_Info {TYPE_1__ secmech; } ;

/* Variables and functions */
 int cifs_alloc_hash (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
smb2_crypto_shash_allocate(struct TCP_Server_Info *server)
{
	return cifs_alloc_hash("hmac(sha256)",
			       &server->secmech.hmacsha256,
			       &server->secmech.sdeschmacsha256);
}