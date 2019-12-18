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
struct bstr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR_P (struct bstr) ; 
 char* talloc_asprintf (void*,char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *standard_volume_url(void *ctx, const char *format,
                                 struct bstr base, int index)
{
    return talloc_asprintf(ctx, format, BSTR_P(base), index);
}