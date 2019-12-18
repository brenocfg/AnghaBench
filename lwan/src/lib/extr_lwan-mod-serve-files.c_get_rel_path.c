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
struct serve_files_priv {int root_path_len; char const* prefix; } ;

/* Variables and functions */
 scalar_t__ streq (char const*,char*) ; 

__attribute__((used)) static const char *get_rel_path(const char *full_path,
                                struct serve_files_priv *priv)
{
    const char *root_path = full_path + priv->root_path_len;

    if (priv->root_path_len == 1) {
        /* If root path length is 1, it's actually "/".   Don't skip
         * the first forward slash if serving from root directory. */
        root_path--;
    }

    if (*root_path)
        return root_path;

    if (streq(priv->prefix, "/"))
        return "";

    return priv->prefix;
}