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
typedef  int /*<<< orphan*/  xmlwriteroutput ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int ARRAY_SIZE (char const*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  write_output_buffer (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static HRESULT write_output_qname(xmlwriteroutput *output, const WCHAR *prefix, const WCHAR *local_name)
{
    if (prefix) {
        static const WCHAR colW[] = {':'};
        write_output_buffer(output, prefix, -1);
        write_output_buffer(output, colW, ARRAY_SIZE(colW));
    }

    write_output_buffer(output, local_name, -1);

    return S_OK;
}