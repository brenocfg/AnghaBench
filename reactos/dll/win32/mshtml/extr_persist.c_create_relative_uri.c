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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {scalar_t__ uri; } ;
typedef  int /*<<< orphan*/  IUri ;
typedef  TYPE_1__ HTMLOuterWindow ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CoInternetCombineUrlEx (scalar_t__,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int URL_DONT_ESCAPE_EXTRA_INFO ; 
 int URL_ESCAPE_SPACES_ONLY ; 
 int /*<<< orphan*/  create_uri (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

HRESULT create_relative_uri(HTMLOuterWindow *window, const WCHAR *rel_uri, IUri **uri)
{
    return window->uri
        ? CoInternetCombineUrlEx(window->uri, rel_uri, URL_ESCAPE_SPACES_ONLY|URL_DONT_ESCAPE_EXTRA_INFO, uri, 0)
        : create_uri(rel_uri, 0, uri);
}