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
typedef  int /*<<< orphan*/  bstr ;

/* Variables and functions */
 scalar_t__ bstrcasecmp0 (int /*<<< orphan*/ ,char*) ; 
 char* bstrto0 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_split_proto (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_url_unescape_inplace (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

char *mp_file_url_to_filename(void *talloc_ctx, bstr url)
{
    bstr proto = mp_split_proto(url, &url);
    if (bstrcasecmp0(proto, "file") != 0)
        return NULL;
    char *filename = bstrto0(talloc_ctx, url);
    mp_url_unescape_inplace(filename);
#if HAVE_DOS_PATHS
    // extract '/' from '/x:/path'
    if (filename[0] == '/' && filename[1] && filename[2] == ':')
        memmove(filename, filename + 1, strlen(filename)); // including \0
#endif
    return filename;
}