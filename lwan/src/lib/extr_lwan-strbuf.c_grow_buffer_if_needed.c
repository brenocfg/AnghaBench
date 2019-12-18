#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* buffer; int /*<<< orphan*/  static_buffer; } ;
struct lwan_strbuf {int flags; int used; TYPE_1__ value; } ;

/* Variables and functions */
 int STATIC ; 
 scalar_t__ UNLIKELY (int) ; 
 size_t align_size (size_t) ; 
 size_t lwan_nextpow2 (int) ; 
 char* malloc (size_t const) ; 
 size_t max (size_t,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 char* realloc (char*,size_t const) ; 

__attribute__((used)) static bool grow_buffer_if_needed(struct lwan_strbuf *s, size_t size)
{
    if (s->flags & STATIC) {
        const size_t aligned_size = align_size(max(size + 1, s->used));
        if (UNLIKELY(!aligned_size))
            return false;

        char *buffer = malloc(aligned_size);
        if (UNLIKELY(!buffer))
            return false;

        memcpy(buffer, s->value.static_buffer, s->used);
        buffer[s->used + 1] = '\0';

        s->flags &= ~STATIC;
        s->value.buffer = buffer;

        return true;
    }

    if (UNLIKELY(!s->used || lwan_nextpow2(s->used) < size)) {
        const size_t aligned_size = align_size(size + 1);
        if (UNLIKELY(!aligned_size))
            return false;

        char *buffer = realloc(s->value.buffer, aligned_size);
        if (UNLIKELY(!buffer))
            return false;
        s->value.buffer = buffer;
    }

    return true;
}