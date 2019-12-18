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
struct pixelformatinfo {scalar_t__ guid; } ;
typedef  int /*<<< orphan*/  WICPixelFormatGUID ;
typedef  size_t UINT ;

/* Variables and functions */
 scalar_t__ IsEqualGUID (scalar_t__,int /*<<< orphan*/  const*) ; 
 struct pixelformatinfo const* supported_formats ; 

__attribute__((used)) static const struct pixelformatinfo *get_formatinfo(const WICPixelFormatGUID *format)
{
    UINT i;

    for (i=0; supported_formats[i].guid; i++)
        if (IsEqualGUID(supported_formats[i].guid, format)) return &supported_formats[i];

    return NULL;
}