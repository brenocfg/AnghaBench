#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * member_0; } ;
struct TYPE_14__ {int /*<<< orphan*/  sink; int /*<<< orphan*/  stream; scalar_t__ location; } ;
struct TYPE_12__ {int /*<<< orphan*/  pwszVal; } ;
struct TYPE_13__ {TYPE_1__ u; void* vt; } ;
typedef  TYPE_2__ PROPVARIANT ;
typedef  TYPE_3__ MimeHtmlProtocol ;
typedef  int /*<<< orphan*/  IMimeMessage ;
typedef  int /*<<< orphan*/  IMimeBody ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HBODY ;
typedef  TYPE_4__ FINDBODY ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BINDSTATUS_MIMETYPEAVAILABLE ; 
 int BSCF_AVAILABLEDATASIZEUNKNOWN ; 
 int BSCF_DATAFULLYAVAILABLE ; 
 int BSCF_FIRSTDATANOTIFICATION ; 
 int BSCF_INTERMEDIATEDATANOTIFICATION ; 
 int BSCF_LASTDATANOTIFICATION ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int FALSE ; 
 int /*<<< orphan*/  IET_DECODED ; 
 int /*<<< orphan*/  IID_IMimeBody ; 
 int /*<<< orphan*/  IInternetProtocolSink_ReportData (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IInternetProtocolSink_ReportProgress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IMimeBody_GetData (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IMimeBody_GetProp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ IMimeMessage_BindToObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IMimeMessage_FindFirst (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ IMimeMessage_FindNext (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ IMimeMessage_GetBodyProp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ MIME_E_NOT_FOUND ; 
 int /*<<< orphan*/  PropVariantClear (TYPE_2__*) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 void* VT_LPWSTR ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__) ; 
 int /*<<< orphan*/  lstrcmpW (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ report_result (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static HRESULT on_mime_message_available(MimeHtmlProtocol *protocol, IMimeMessage *mime_message)
{
    FINDBODY find = {NULL};
    IMimeBody *mime_body;
    PROPVARIANT value;
    HBODY body;
    HRESULT hres;

    hres = IMimeMessage_FindFirst(mime_message, &find, &body);
    if(FAILED(hres))
        return report_result(protocol, hres);

    if(protocol->location) {
        BOOL found = FALSE;
        do {
            hres = IMimeMessage_FindNext(mime_message, &find, &body);
            if(FAILED(hres)) {
                WARN("location %s not found\n", debugstr_w(protocol->location));
                return report_result(protocol, hres);
            }

            value.vt = VT_LPWSTR;
            hres = IMimeMessage_GetBodyProp(mime_message, body, "content-location", 0, &value);
            if(hres == MIME_E_NOT_FOUND)
                continue;
            if(FAILED(hres))
                return report_result(protocol, hres);

            found = !lstrcmpW(protocol->location, value.u.pwszVal);
            PropVariantClear(&value);
        }while(!found);
    }else {
        hres = IMimeMessage_FindNext(mime_message, &find, &body);
        if(FAILED(hres)) {
            WARN("location %s not found\n", debugstr_w(protocol->location));
            return report_result(protocol, hres);
        }
    }

    hres = IMimeMessage_BindToObject(mime_message, body, &IID_IMimeBody, (void**)&mime_body);
    if(FAILED(hres))
        return report_result(protocol, hres);

    value.vt = VT_LPWSTR;
    hres = IMimeBody_GetProp(mime_body, "content-type", 0, &value);
    if(SUCCEEDED(hres)) {
        hres = IInternetProtocolSink_ReportProgress(protocol->sink, BINDSTATUS_MIMETYPEAVAILABLE, value.u.pwszVal);
        PropVariantClear(&value);
    }

    /* FIXME: Create and report cache file. */

    hres = IMimeBody_GetData(mime_body, IET_DECODED, &protocol->stream);
    if(FAILED(hres))
        return report_result(protocol, hres);

    IInternetProtocolSink_ReportData(protocol->sink, BSCF_FIRSTDATANOTIFICATION
                                     | BSCF_INTERMEDIATEDATANOTIFICATION
                                     | BSCF_LASTDATANOTIFICATION
                                     | BSCF_DATAFULLYAVAILABLE
                                     | BSCF_AVAILABLEDATASIZEUNKNOWN, 0, 0);

    return report_result(protocol, S_OK);
}