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
struct scatterlist {int /*<<< orphan*/  length; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,struct scatterlist*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int crypto_ahash_update (struct ahash_request*) ; 

__attribute__((used)) static int
checksummer(struct scatterlist *sg, void *data)
{
	struct ahash_request *req = data;

	ahash_request_set_crypt(req, sg, NULL, sg->length);

	return crypto_ahash_update(req);
}