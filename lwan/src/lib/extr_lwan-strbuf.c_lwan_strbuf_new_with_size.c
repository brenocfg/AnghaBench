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
struct lwan_strbuf {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DYNAMICALLY_ALLOCATED ; 
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  free (struct lwan_strbuf*) ; 
 int /*<<< orphan*/  lwan_strbuf_init_with_size (struct lwan_strbuf*,size_t) ; 
 struct lwan_strbuf* malloc (int) ; 

struct lwan_strbuf *lwan_strbuf_new_with_size(size_t size)
{
    struct lwan_strbuf *s = malloc(sizeof(*s));

    if (UNLIKELY(!lwan_strbuf_init_with_size(s, size))) {
        free(s);

        return NULL;
    }

    s->flags |= DYNAMICALLY_ALLOCATED;

    return s;
}