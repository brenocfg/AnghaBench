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
struct bstr {int dummy; } ;

/* Variables and functions */
 struct bstr bstr_cut (struct bstr,int) ; 
 scalar_t__ bstr_startswith0 (struct bstr,char*) ; 

__attribute__((used)) static struct bstr skip_utf8_bom(struct bstr data)
{
    return bstr_startswith0(data, "\xEF\xBB\xBF") ? bstr_cut(data, 3) : data;
}