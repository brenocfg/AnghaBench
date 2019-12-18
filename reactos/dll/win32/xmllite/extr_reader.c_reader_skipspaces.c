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
typedef  int /*<<< orphan*/  xmlreader ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;

/* Variables and functions */
 scalar_t__ is_wchar_space (int /*<<< orphan*/  const) ; 
 int reader_get_cur (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * reader_get_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_skipn (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int reader_skipspaces(xmlreader *reader)
{
    const WCHAR *ptr = reader_get_ptr(reader);
    UINT start = reader_get_cur(reader);

    while (is_wchar_space(*ptr))
    {
        reader_skipn(reader, 1);
        ptr = reader_get_ptr(reader);
    }

    return reader_get_cur(reader) - start;
}