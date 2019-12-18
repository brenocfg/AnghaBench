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
typedef  int /*<<< orphan*/  HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_Stream ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_REAL ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 char* HPDF_FToA (char*,int /*<<< orphan*/ ,char*) ; 
 int HPDF_REAL_LEN ; 
 int /*<<< orphan*/  HPDF_Stream_Write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

HPDF_STATUS
HPDF_Stream_WriteReal  (HPDF_Stream  stream,
                        HPDF_REAL    value)
{
    char buf[HPDF_REAL_LEN + 1];

    char* p = HPDF_FToA(buf, value, buf + HPDF_REAL_LEN);

    return HPDF_Stream_Write(stream, (HPDF_BYTE *)buf, (HPDF_UINT)(p - buf));
}