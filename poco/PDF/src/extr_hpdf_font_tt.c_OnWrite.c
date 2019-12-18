#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  (* write_fn ) (TYPE_4__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  attr; } ;
struct TYPE_8__ {size_t first_char; size_t last_char; } ;
struct TYPE_7__ {int /*<<< orphan*/  attr; } ;
struct TYPE_6__ {TYPE_4__* encoder; int /*<<< orphan*/ * widths; } ;
typedef  size_t HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_Stream ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_1__* HPDF_FontAttr ;
typedef  TYPE_2__* HPDF_Dict ;
typedef  TYPE_3__* HPDF_BasicEncoderAttr ;

/* Variables and functions */
 char* HPDF_IToA (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_StrCpy (char*,char*,char*) ; 
 int /*<<< orphan*/  HPDF_Stream_WriteEscapeName (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HPDF_Stream_WriteStr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HPDF_STATUS
OnWrite  (HPDF_Dict    obj,
          HPDF_Stream  stream)
{
    HPDF_FontAttr attr = (HPDF_FontAttr)obj->attr;
    HPDF_BasicEncoderAttr encoder_attr =
                    (HPDF_BasicEncoderAttr)attr->encoder->attr;
    HPDF_UINT i;
    HPDF_STATUS ret;
    char buf[128];
    char *pbuf = buf;
    char *eptr = buf + 127;

    HPDF_PTRACE ((" HPDF_Font_OnWrite\n"));

    /* Widths entry */
    if ((ret = HPDF_Stream_WriteEscapeName (stream, "Widths")) != HPDF_OK)
        return ret;

    if ((ret = HPDF_Stream_WriteStr (stream, " [\012")) != HPDF_OK)
        return ret;

    for (i = encoder_attr->first_char; i <= encoder_attr->last_char; i++) {

        pbuf = HPDF_IToA (pbuf, attr->widths[i], eptr);
        *pbuf++ = ' ';

        if ((i + 1) % 16 == 0) {
            HPDF_StrCpy(pbuf, "\012", eptr);
            if ((ret = HPDF_Stream_WriteStr (stream, buf)) != HPDF_OK)
                return ret;
            pbuf = buf;
        }

    }

    HPDF_StrCpy (pbuf, "]\012", eptr);

    if ((ret = HPDF_Stream_WriteStr (stream, buf)) != HPDF_OK)
        return ret;

    return attr->encoder->write_fn (attr->encoder, stream);
}