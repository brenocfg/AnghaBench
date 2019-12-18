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
struct TYPE_3__ {char const* tmp_dir; } ;
typedef  TYPE_1__ install_ctx_t ;
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char const*) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* strchrW (char const*,char) ; 
 int /*<<< orphan*/  strcpyW (char*,char const*) ; 
 size_t strlenW (char const*) ; 
 int /*<<< orphan*/  strncmpiW (char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void expand_command(install_ctx_t *ctx, const WCHAR *cmd, WCHAR *buf, size_t *size)
{
    const WCHAR *ptr = cmd, *prev_ptr = cmd;
    size_t len = 0, len2;

    static const WCHAR expand_dirW[] = {'%','E','X','T','R','A','C','T','_','D','I','R','%'};

    while((ptr = strchrW(ptr, '%'))) {
        if(buf)
            memcpy(buf+len, prev_ptr, ptr-prev_ptr);
        len += ptr-prev_ptr;

        if(!strncmpiW(ptr, expand_dirW, ARRAY_SIZE(expand_dirW))) {
            len2 = strlenW(ctx->tmp_dir);
            if(buf)
                memcpy(buf+len, ctx->tmp_dir, len2*sizeof(WCHAR));
            len += len2;
            ptr += ARRAY_SIZE(expand_dirW);
        }else {
            FIXME("Can't expand %s\n", debugstr_w(ptr));
            if(buf)
                buf[len] = '%';
            len++;
            ptr++;
        }

        prev_ptr = ptr;
    }

    if(buf)
        strcpyW(buf+len, prev_ptr);
    *size = len + strlenW(prev_ptr) + 1;
}