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
struct rtw_cbuf {int write; int read; } ;

/* Variables and functions */
 int _FALSE ; 
 int _TRUE ; 

inline bool rtw_cbuf_full(struct rtw_cbuf *cbuf)
{
	return (cbuf->write == cbuf->read-1)? _TRUE : _FALSE;
}