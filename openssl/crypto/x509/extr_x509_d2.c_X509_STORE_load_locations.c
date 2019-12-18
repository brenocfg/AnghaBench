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
typedef  int /*<<< orphan*/  X509_STORE ;

/* Variables and functions */
 int /*<<< orphan*/  X509_STORE_load_file (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  X509_STORE_load_path (int /*<<< orphan*/ *,char const*) ; 

int X509_STORE_load_locations(X509_STORE *ctx, const char *file,
                              const char *path)
{
    if (file == NULL && path == NULL)
        return 0;
    if (file != NULL && !X509_STORE_load_file(ctx, file))
        return 0;
    if (path != NULL && !X509_STORE_load_path(ctx, path))
        return 0;
    return 1;
}