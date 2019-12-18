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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CreateUri (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int Uri_CREATE_ALLOW_IMPLICIT_FILE_SCHEME ; 

HRESULT create_uri(const WCHAR *uri_str, DWORD flags, IUri **uri)
{
    return CreateUri(uri_str, flags | Uri_CREATE_ALLOW_IMPLICIT_FILE_SCHEME, 0, uri);
}