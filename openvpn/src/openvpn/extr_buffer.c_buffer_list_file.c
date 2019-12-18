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
struct buffer_list {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct buffer_list* buffer_list_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_list_push (struct buffer_list*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/ * platform_fopen (char const*,char*) ; 

struct buffer_list *
buffer_list_file(const char *fn, int max_line_len)
{
    FILE *fp = platform_fopen(fn, "r");
    struct buffer_list *bl = NULL;

    if (fp)
    {
        char *line = (char *) malloc(max_line_len);
        if (line)
        {
            bl = buffer_list_new(0);
            while (fgets(line, max_line_len, fp) != NULL)
            {
                buffer_list_push(bl, line);
            }
            free(line);
        }
        fclose(fp);
    }
    return bl;
}