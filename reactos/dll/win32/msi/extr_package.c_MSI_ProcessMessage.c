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
typedef  char WCHAR ;
struct TYPE_4__ {char* LastAction; char* LastActionTemplate; int /*<<< orphan*/  db; } ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int INSTALLMESSAGE ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
#define  INSTALLMESSAGE_ACTIONDATA 136 
#define  INSTALLMESSAGE_ACTIONSTART 135 
#define  INSTALLMESSAGE_COMMONDATA 134 
#define  INSTALLMESSAGE_ERROR 133 
#define  INSTALLMESSAGE_FATALEXIT 132 
#define  INSTALLMESSAGE_INFO 131 
#define  INSTALLMESSAGE_OUTOFDISKSPACE 130 
#define  INSTALLMESSAGE_USER 129 
#define  INSTALLMESSAGE_WARNING 128 
 int MSIERR_ACTIONSTART ; 
 int MSIERR_COMMONDATA ; 
 int MSIERR_INSTALLERROR ; 
 int MSI_NULL_INTEGER ; 
 int /*<<< orphan*/  MSI_ProcessMessageVerbatim (TYPE_1__*,int const,int /*<<< orphan*/ *) ; 
 int MSI_RecordGetInteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MSI_RecordIsNull (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSI_RecordSetStringW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_internal_error_message (int) ; 
 char* msi_alloc (int) ; 
 void* msi_dup_record_field (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msi_free (char*) ; 
 char* msi_get_error_message (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,char*,char*) ; 
 int /*<<< orphan*/  strcatW (char*,char*) ; 
 int /*<<< orphan*/  strcpyW (char*,char*) ; 
 void* strdupW (int /*<<< orphan*/ ) ; 
 scalar_t__ strlenW (char*) ; 
 int /*<<< orphan*/  szEmpty ; 

INT MSI_ProcessMessage( MSIPACKAGE *package, INSTALLMESSAGE eMessageType, MSIRECORD *record )
{
    switch (eMessageType & 0xff000000)
    {
    case INSTALLMESSAGE_FATALEXIT:
    case INSTALLMESSAGE_ERROR:
    case INSTALLMESSAGE_WARNING:
    case INSTALLMESSAGE_USER:
    case INSTALLMESSAGE_INFO:
    case INSTALLMESSAGE_OUTOFDISKSPACE:
        if (MSI_RecordGetInteger(record, 1) != MSI_NULL_INTEGER)
        {
            /* error message */

            LPWSTR template;
            LPWSTR template_rec = NULL, template_prefix = NULL;
            int error = MSI_RecordGetInteger(record, 1);

            if (MSI_RecordIsNull(record, 0))
            {
                if (error >= 32)
                {
                    template_rec = msi_get_error_message(package->db, error);

                    if (!template_rec && error >= 2000)
                    {
                        /* internal error, not localized */
                        if ((template_rec = (LPWSTR) get_internal_error_message(error)))
                        {
                            MSI_RecordSetStringW(record, 0, template_rec);
                            MSI_ProcessMessageVerbatim(package, INSTALLMESSAGE_INFO, record);
                        }
                        template_rec = msi_get_error_message(package->db, MSIERR_INSTALLERROR);
                        MSI_RecordSetStringW(record, 0, template_rec);
                        MSI_ProcessMessageVerbatim(package, eMessageType, record);
                        msi_free(template_rec);
                        return 0;
                    }
                }
            }
            else
                template_rec = msi_dup_record_field(record, 0);

            template_prefix = msi_get_error_message(package->db, eMessageType >> 24);
            if (!template_prefix) template_prefix = strdupW(szEmpty);

            if (!template_rec)
            {
                /* always returns 0 */
                MSI_RecordSetStringW(record, 0, template_prefix);
                MSI_ProcessMessageVerbatim(package, eMessageType, record);
                msi_free(template_prefix);
                return 0;
            }

            template = msi_alloc((strlenW(template_rec) + strlenW(template_prefix) + 1) * sizeof(WCHAR));
            if (!template) return ERROR_OUTOFMEMORY;

            strcpyW(template, template_prefix);
            strcatW(template, template_rec);
            MSI_RecordSetStringW(record, 0, template);

            msi_free(template_prefix);
            msi_free(template_rec);
            msi_free(template);
        }
        break;
    case INSTALLMESSAGE_ACTIONSTART:
    {
        WCHAR *template = msi_get_error_message(package->db, MSIERR_ACTIONSTART);
        MSI_RecordSetStringW(record, 0, template);
        msi_free(template);

        msi_free(package->LastAction);
        msi_free(package->LastActionTemplate);
        package->LastAction = msi_dup_record_field(record, 1);
        if (!package->LastAction) package->LastAction = strdupW(szEmpty);
        package->LastActionTemplate = msi_dup_record_field(record, 3);
        break;
    }
    case INSTALLMESSAGE_ACTIONDATA:
        if (package->LastAction && package->LastActionTemplate)
        {
            static const WCHAR template_s[] =
                {'{','{','%','s',':',' ','}','}','%','s',0};
            WCHAR *template;

            template = msi_alloc((strlenW(package->LastAction) + strlenW(package->LastActionTemplate) + 7) * sizeof(WCHAR));
            if (!template) return ERROR_OUTOFMEMORY;
            sprintfW(template, template_s, package->LastAction, package->LastActionTemplate);
            MSI_RecordSetStringW(record, 0, template);
            msi_free(template);
        }
        break;
    case INSTALLMESSAGE_COMMONDATA:
    {
        WCHAR *template = msi_get_error_message(package->db, MSIERR_COMMONDATA);
        MSI_RecordSetStringW(record, 0, template);
        msi_free(template);
    }
    break;
    }

    return MSI_ProcessMessageVerbatim(package, eMessageType, record);
}