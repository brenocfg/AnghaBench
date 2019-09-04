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
struct TYPE_3__ {int md_size; scalar_t__ (* size ) () ;int /*<<< orphan*/ * prov; } ;
typedef  TYPE_1__ EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_MD_SIZE ; 
 int /*<<< orphan*/  EVP_R_MESSAGE_DIGEST_IS_NULL ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 () ; 

int EVP_MD_size(const EVP_MD *md)
{
    if (!md) {
        EVPerr(EVP_F_EVP_MD_SIZE, EVP_R_MESSAGE_DIGEST_IS_NULL);
        return -1;
    }

    if (md->prov != NULL && md->size != NULL)
        return (int)md->size();

    return md->md_size;
}