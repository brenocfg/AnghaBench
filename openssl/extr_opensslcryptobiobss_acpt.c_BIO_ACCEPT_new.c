#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int accept_sock; int /*<<< orphan*/  accept_family; } ;
typedef  TYPE_1__ BIO_ACCEPT ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_FAMILY_IPANY ; 
 int /*<<< orphan*/  BIO_F_BIO_ACCEPT_NEW ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ INVALID_SOCKET ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 

__attribute__((used)) static BIO_ACCEPT *BIO_ACCEPT_new(void)
{
    BIO_ACCEPT *ret;

    if ((ret = OPENSSL_zalloc(sizeof(*ret))) == NULL) {
        BIOerr(BIO_F_BIO_ACCEPT_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    ret->accept_family = BIO_FAMILY_IPANY;
    ret->accept_sock = (int)INVALID_SOCKET;
    return ret;
}