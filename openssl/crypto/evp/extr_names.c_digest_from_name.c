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
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_NAME_TYPE_MD_METH ; 
 scalar_t__ OBJ_NAME_get (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void digest_from_name(const char *name, void *data)
{
    const EVP_MD **md = data;

    if (*md != NULL)
        return;

    *md = (const EVP_MD *)OBJ_NAME_get(name, OBJ_NAME_TYPE_MD_METH);
}