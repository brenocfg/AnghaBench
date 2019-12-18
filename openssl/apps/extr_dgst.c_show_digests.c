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
struct doall_dgst_digests {int n; int /*<<< orphan*/  bio; } ;
struct TYPE_3__ {scalar_t__* name; } ;
typedef  TYPE_1__ OBJ_NAME ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * EVP_get_digestbyname (scalar_t__*) ; 
 int /*<<< orphan*/  islower (unsigned char) ; 
 int /*<<< orphan*/ * strstr (scalar_t__*,char*) ; 

__attribute__((used)) static void show_digests(const OBJ_NAME *name, void *arg)
{
    struct doall_dgst_digests *dec = (struct doall_dgst_digests *)arg;
    const EVP_MD *md = NULL;

    /* Filter out signed digests (a.k.a signature algorithms) */
    if (strstr(name->name, "rsa") != NULL || strstr(name->name, "RSA") != NULL)
        return;

    if (!islower((unsigned char)*name->name))
        return;

    /* Filter out message digests that we cannot use */
    md = EVP_get_digestbyname(name->name);
    if (md == NULL)
        return;

    BIO_printf(dec->bio, "-%-25s", name->name);
    if (++dec->n == 3) {
        BIO_printf(dec->bio, "\n");
        dec->n = 0;
    } else {
        BIO_printf(dec->bio, " ");
    }
}