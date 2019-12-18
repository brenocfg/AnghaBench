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
typedef  int /*<<< orphan*/  stringify_ctx_t ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  append_string_len (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static inline BOOL append_simple_quote(stringify_ctx_t *ctx, WCHAR c)
{
    WCHAR str[] = {'\\',c};
    return append_string_len(ctx, str, 2);
}