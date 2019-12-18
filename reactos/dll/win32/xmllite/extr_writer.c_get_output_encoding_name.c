#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  encoding; int /*<<< orphan*/  const* encoding_name; } ;
typedef  TYPE_1__ xmlwriteroutput ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  const* get_encoding_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const WCHAR *get_output_encoding_name(xmlwriteroutput *output)
{
    if (output->encoding_name)
        return output->encoding_name;

    return get_encoding_name(output->encoding);
}