#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_4__ {scalar_t__ error_no; } ;
struct TYPE_5__ {TYPE_1__ error; int /*<<< orphan*/  mmgr; int /*<<< orphan*/  trailer; } ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_MD5_CTX ;
typedef  TYPE_2__* HPDF_Doc ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;
typedef  scalar_t__ HPDF_Array ;

/* Variables and functions */
 scalar_t__ HPDF_Array_Add (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Array_New (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Binary_New (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ HPDF_Dict_Add (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ HPDF_Dict_GetItem (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_MD5Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HPDF_MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HPDF_MD5Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int HPDF_MD5_KEY_LEN ; 
 int /*<<< orphan*/  HPDF_OCLASS_ARRAY ; 
 scalar_t__ HPDF_OK ; 
 int HPDF_StrLen (char const*,int) ; 
 scalar_t__ ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

HPDF_STATUS
HPDF_PDFA_GenerateID(HPDF_Doc pdf)
{
    HPDF_Array id;
    HPDF_BYTE *currentTime;
    HPDF_BYTE idkey[HPDF_MD5_KEY_LEN];
    HPDF_MD5_CTX md5_ctx;
    time_t ltime; 

    ltime = time(NULL); 
    currentTime = (HPDF_BYTE *)ctime(&ltime);
        
    id = HPDF_Dict_GetItem(pdf->trailer, "ID", HPDF_OCLASS_ARRAY);
    if (!id) {
       id = HPDF_Array_New(pdf->mmgr);

       if (!id || HPDF_Dict_Add(pdf->trailer, "ID", id) != HPDF_OK)
         return pdf->error.error_no;
       
       HPDF_MD5Init(&md5_ctx);
       HPDF_MD5Update(&md5_ctx, (HPDF_BYTE *) "libHaru", sizeof("libHaru") - 1);
       HPDF_MD5Update(&md5_ctx, currentTime, HPDF_StrLen((const char *)currentTime, -1));
       HPDF_MD5Final(idkey, &md5_ctx);
       
       if (HPDF_Array_Add (id, HPDF_Binary_New (pdf->mmgr, idkey, HPDF_MD5_KEY_LEN)) != HPDF_OK)
         return pdf->error.error_no;

       if (HPDF_Array_Add (id, HPDF_Binary_New (pdf->mmgr,idkey,HPDF_MD5_KEY_LEN)) != HPDF_OK)
         return pdf->error.error_no;
    
       return HPDF_OK;
    }
    
    return HPDF_OK;
}