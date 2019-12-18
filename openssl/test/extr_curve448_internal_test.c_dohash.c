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
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  hashout ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestFinalXOF (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  EVP_shake256 () ; 

__attribute__((used)) static const uint8_t *dohash(EVP_MD_CTX *hashctx, const uint8_t *msg,
                             size_t msglen)
{
    static uint8_t hashout[64];

    if (!EVP_DigestInit_ex(hashctx, EVP_shake256(), NULL)
            || !EVP_DigestUpdate(hashctx, msg, msglen)
            || !EVP_DigestFinalXOF(hashctx, hashout, sizeof(hashout)))
        return NULL;

    return hashout;
}