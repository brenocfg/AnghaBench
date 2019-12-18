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
struct gc_arena {int dummy; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 char const* BSTR (struct buffer*) ; 
 int CC_ASTERISK ; 
 int CC_BACKSLASH ; 
 int CC_COLON ; 
 int CC_DOUBLE_QUOTE ; 
 int CC_GREATER_THAN ; 
 int CC_LESS_THAN ; 
 int CC_PIPE ; 
 int /*<<< orphan*/  CC_PRINT ; 
 int CC_QUESTION_MARK ; 
 int CC_SLASH ; 
 char OS_SPECIFIC_DIRSEP ; 
 struct buffer alloc_buf_gc (size_t const,struct gc_arena*) ; 
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,char const*,...) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* string_mod_const (char const*,int /*<<< orphan*/ ,int const,char,struct gc_arena*) ; 
 int strlen (char const*) ; 
 scalar_t__ win_safe_filename (char const*) ; 

const char *
platform_gen_path(const char *directory, const char *filename,
                  struct gc_arena *gc)
{
#ifdef _WIN32
    const int CC_PATH_RESERVED = CC_LESS_THAN|CC_GREATER_THAN|CC_COLON
                                 |CC_DOUBLE_QUOTE|CC_SLASH|CC_BACKSLASH|CC_PIPE|CC_QUESTION_MARK|CC_ASTERISK;
#else
    const int CC_PATH_RESERVED = CC_SLASH;
#endif

    if (!gc)
    {
        return NULL; /* Would leak memory otherwise */
    }

    const char *safe_filename = string_mod_const(filename, CC_PRINT, CC_PATH_RESERVED, '_', gc);

    if (safe_filename
        && strcmp(safe_filename, ".")
        && strcmp(safe_filename, "..")
#ifdef _WIN32
        && win_safe_filename(safe_filename)
#endif
        )
    {
        const size_t outsize = strlen(safe_filename) + (directory ? strlen(directory) : 0) + 16;
        struct buffer out = alloc_buf_gc(outsize, gc);
        char dirsep[2];

        dirsep[0] = OS_SPECIFIC_DIRSEP;
        dirsep[1] = '\0';

        if (directory)
        {
            buf_printf(&out, "%s%s", directory, dirsep);
        }
        buf_printf(&out, "%s", safe_filename);

        return BSTR(&out);
    }
    else
    {
        return NULL;
    }
}