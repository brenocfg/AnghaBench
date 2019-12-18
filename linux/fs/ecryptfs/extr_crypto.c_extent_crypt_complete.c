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
struct extent_crypt_result {int rc; int /*<<< orphan*/  completion; } ;
struct crypto_async_request {struct extent_crypt_result* data; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void extent_crypt_complete(struct crypto_async_request *req, int rc)
{
	struct extent_crypt_result *ecr = req->data;

	if (rc == -EINPROGRESS)
		return;

	ecr->rc = rc;
	complete(&ecr->completion);
}