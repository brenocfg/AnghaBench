#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* to_unicode_fn ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  HPDF_UNICODE ;
typedef  int /*<<< orphan*/  HPDF_UINT16 ;
typedef  TYPE_1__* HPDF_Encoder ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

HPDF_UNICODE
HPDF_Encoder_ToUnicode  (HPDF_Encoder     encoder,
                         HPDF_UINT16      code)
{
    return encoder->to_unicode_fn (encoder, code);
}