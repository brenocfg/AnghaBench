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
struct bstr {scalar_t__ start; } ;

/* Variables and functions */
 char* bstrdup0 (void*,struct bstr) ; 
 char* talloc_strdup (void*,char*) ; 

__attribute__((used)) static inline char *bstrto0(void *talloc_ctx, struct bstr str)
{
    return str.start ? bstrdup0(talloc_ctx, str) : talloc_strdup(talloc_ctx, "");
}