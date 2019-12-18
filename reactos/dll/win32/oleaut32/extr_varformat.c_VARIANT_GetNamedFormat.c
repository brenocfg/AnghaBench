#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  const* format; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ NAMED_FORMAT ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_2__* LPCNAMED_FORMAT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FormatCompareFn ; 
 int /*<<< orphan*/  VARIANT_NamedFormats ; 
 TYPE_2__* bsearch (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline const BYTE *VARIANT_GetNamedFormat(LPCWSTR lpszFormat)
{
  NAMED_FORMAT key;
  LPCNAMED_FORMAT fmt;

  key.name = lpszFormat;
  fmt = bsearch(&key, VARIANT_NamedFormats, ARRAY_SIZE(VARIANT_NamedFormats),
                                 sizeof(NAMED_FORMAT), FormatCompareFn);
  return fmt ? fmt->format : NULL;
}