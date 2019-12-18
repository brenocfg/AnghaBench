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
struct lwan_strbuf {int dummy; } ;

/* Variables and functions */
 int lwan_strbuf_set_static (struct lwan_strbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static inline bool lwan_strbuf_set_staticz(struct lwan_strbuf *s1,
                                           const char *s2)
{
    return lwan_strbuf_set_static(s1, s2, strlen(s2));
}