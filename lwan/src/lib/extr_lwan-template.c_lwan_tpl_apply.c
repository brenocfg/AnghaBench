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
struct lwan_tpl {int /*<<< orphan*/  minimum_size; } ;
struct lwan_strbuf {int dummy; } ;

/* Variables and functions */
 scalar_t__ LIKELY (int /*<<< orphan*/ ) ; 
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  lwan_strbuf_free (struct lwan_strbuf*) ; 
 struct lwan_strbuf* lwan_strbuf_new_with_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwan_tpl_apply_with_buffer (struct lwan_tpl*,struct lwan_strbuf*,void*) ; 

struct lwan_strbuf *lwan_tpl_apply(struct lwan_tpl *tpl, void *variables)
{
    struct lwan_strbuf *buf = lwan_strbuf_new_with_size(tpl->minimum_size);

    if (UNLIKELY(!buf))
        return NULL;

    if (LIKELY(lwan_tpl_apply_with_buffer(tpl, buf, variables)))
        return buf;

    lwan_strbuf_free(buf);
    return NULL;
}