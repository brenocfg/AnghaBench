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
struct serve_files_priv {struct serve_files_priv* prefix; struct serve_files_priv* root_path; int /*<<< orphan*/  root_fd; int /*<<< orphan*/  cache; int /*<<< orphan*/  directory_list_tpl; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct serve_files_priv*) ; 
 int /*<<< orphan*/  lwan_status_warning (char*) ; 
 int /*<<< orphan*/  lwan_tpl_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void serve_files_destroy(void *data)
{
    struct serve_files_priv *priv = data;

    if (!priv) {
        lwan_status_warning("Nothing to shutdown");
        return;
    }

    lwan_tpl_free(priv->directory_list_tpl);
    cache_destroy(priv->cache);
    close(priv->root_fd);
    free(priv->root_path);
    free(priv->prefix);
    free(priv);
}