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
struct file {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strdupW (int /*<<< orphan*/  const*) ; 
 int strlenW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strrchrW (int /*<<< orphan*/  const*,char) ; 

__attribute__((used)) static WCHAR *build_source_filename( const WCHAR *manifest, struct file *file )
{
    WCHAR *src;
    const WCHAR *p;
    int len;

    p = strrchrW( manifest, '\\' );
    if (!p) p = strrchrW( manifest, '/' );
    if (!p) return strdupW( manifest );

    len = p - manifest + 1;
    if (!(src = HeapAlloc( GetProcessHeap(), 0, (len + strlenW( file->name ) + 1) * sizeof(WCHAR) )))
        return NULL;

    memcpy( src, manifest, len * sizeof(WCHAR) );
    strcpyW( src + len, file->name );
    return src;
}