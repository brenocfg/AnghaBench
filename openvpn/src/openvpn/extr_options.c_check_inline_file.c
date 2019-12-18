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
struct in_src {int dummy; } ;
struct gc_arena {int dummy; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR (struct buffer*) ; 
 char* INLINE_FILE_TAG ; 
 struct buffer alloc_buf (int) ; 
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,char*) ; 
 int /*<<< orphan*/  free_buf (struct buffer*) ; 
 char* read_inline_file (struct in_src*,int /*<<< orphan*/ ,struct gc_arena*) ; 
 char* string_alloc (char*,struct gc_arena*) ; 
 int strlen (char*) ; 

__attribute__((used)) static bool
check_inline_file(struct in_src *is, char *p[], struct gc_arena *gc)
{
    bool ret = false;
    if (p[0] && !p[1])
    {
        char *arg = p[0];
        if (arg[0] == '<' && arg[strlen(arg)-1] == '>')
        {
            struct buffer close_tag;
            arg[strlen(arg)-1] = '\0';
            p[0] = string_alloc(arg+1, gc);
            p[1] = string_alloc(INLINE_FILE_TAG, gc);
            close_tag = alloc_buf(strlen(p[0]) + 4);
            buf_printf(&close_tag, "</%s>", p[0]);
            p[2] = read_inline_file(is, BSTR(&close_tag), gc);
            p[3] = NULL;
            free_buf(&close_tag);
            ret = true;
        }
    }
    return ret;
}