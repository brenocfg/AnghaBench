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
struct stat {int dummy; } ;
struct serve_files_priv {int /*<<< orphan*/  directory_list_tpl; } ;
struct lwan_value {int /*<<< orphan*/  len; int /*<<< orphan*/  value; } ;
struct lwan_strbuf {int dummy; } ;
struct file_list {char const* full_path; int /*<<< orphan*/  readme; int /*<<< orphan*/  rel_path; } ;
struct dir_list_cache_data {struct lwan_strbuf rendered; int /*<<< orphan*/  deflated; int /*<<< orphan*/  brotli; } ;
struct file_cache_entry {char* mime_type; struct dir_list_cache_data dir_list_cache_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  brotli_value (struct lwan_value*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deflate_value (struct lwan_value*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dirlist_find_readme (struct lwan_strbuf*,struct serve_files_priv*,char const*) ; 
 int /*<<< orphan*/  get_rel_path (char const*,struct serve_files_priv*) ; 
 int /*<<< orphan*/  lwan_strbuf_free (struct lwan_strbuf*) ; 
 int /*<<< orphan*/  lwan_strbuf_get_buffer (struct lwan_strbuf*) ; 
 int /*<<< orphan*/  lwan_strbuf_get_length (struct lwan_strbuf*) ; 
 int /*<<< orphan*/  lwan_strbuf_init (struct lwan_strbuf*) ; 
 int /*<<< orphan*/  lwan_tpl_apply_with_buffer (int /*<<< orphan*/ ,struct lwan_strbuf*,struct file_list*) ; 

__attribute__((used)) static bool dirlist_init(struct file_cache_entry *ce,
                         struct serve_files_priv *priv,
                         const char *full_path,
                         struct stat *st __attribute__((unused)))
{
    struct dir_list_cache_data *dd = &ce->dir_list_cache_data;
    struct lwan_strbuf readme;
    bool ret = false;

    if (!lwan_strbuf_init(&readme))
        return false;
    if (!lwan_strbuf_init(&dd->rendered))
        goto out_free_readme;

    struct file_list vars = {
        .full_path = full_path,
        .rel_path = get_rel_path(full_path, priv),
        .readme = dirlist_find_readme(&readme, priv, full_path),
    };

    if (!lwan_tpl_apply_with_buffer(priv->directory_list_tpl, &dd->rendered,
                                    &vars))
        goto out_free_rendered;

    ce->mime_type = "text/html";

    struct lwan_value rendered = {
        .value = lwan_strbuf_get_buffer(&dd->rendered),
        .len = lwan_strbuf_get_length(&dd->rendered),
    };
    deflate_value(&rendered, &dd->deflated);
#if defined(HAVE_BROTLI)
    brotli_value(&rendered, &dd->brotli, &dd->deflated);
#endif

    ret = true;
    goto out_free_readme;

out_free_rendered:
    lwan_strbuf_free(&dd->rendered);
out_free_readme:
    lwan_strbuf_free(&readme);
    return ret;
}