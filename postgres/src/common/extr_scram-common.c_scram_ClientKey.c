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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  scram_HMAC_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  SCRAM_KEY_LEN ; 
 int /*<<< orphan*/  scram_HMAC_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scram_HMAC_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scram_HMAC_update (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

void
scram_ClientKey(const uint8 *salted_password, uint8 *result)
{
	scram_HMAC_ctx ctx;

	scram_HMAC_init(&ctx, salted_password, SCRAM_KEY_LEN);
	scram_HMAC_update(&ctx, "Client Key", strlen("Client Key"));
	scram_HMAC_final(result, &ctx);
}