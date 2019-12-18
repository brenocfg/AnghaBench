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
struct inf_section {int dummy; } ;
struct inf_file {char* content; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 char* get_next_line (char**,char**) ; 
 int /*<<< orphan*/  inf_section_parse (struct inf_file*,char*,char*,struct inf_section**) ; 
 int /*<<< orphan*/  inf_value_parse (struct inf_section*,char*) ; 
 scalar_t__ strchr (char*,char) ; 

__attribute__((used)) static HRESULT inf_process_content(struct inf_file *inf)
{
    struct inf_section *section = NULL;
    char *content = inf->content;
    char *line, *last_chr;
    HRESULT hr = S_OK;

    while (SUCCEEDED(hr) && (line = get_next_line(&content, &last_chr)))
    {
        if (*line == '[')
            hr = inf_section_parse(inf, line, last_chr, &section);
        else if (strchr(line, '=') && section)
            hr = inf_value_parse(section, line);
    }

    return hr;
}