#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ver ;
struct table {scalar_t__ num_rows; scalar_t__ data; } ;
struct record_operatingsystem {int freephysicalmemory; int osproductsuite; int ostype; int primary; int suitemask; int totalvirtualmemorysize; int totalvisiblememorysize; int /*<<< orphan*/  version; int /*<<< orphan*/  systemdirectory; int /*<<< orphan*/  servicepackminor; int /*<<< orphan*/  servicepackmajor; int /*<<< orphan*/  serialnumber; int /*<<< orphan*/  oslanguage; int /*<<< orphan*/  osarchitecture; int /*<<< orphan*/  caption; int /*<<< orphan*/  name; int /*<<< orphan*/  locale; int /*<<< orphan*/  localdatetime; int /*<<< orphan*/  lastbootuptime; int /*<<< orphan*/  installdate; int /*<<< orphan*/ * csdversion; int /*<<< orphan*/  countrycode; int /*<<< orphan*/  codeset; int /*<<< orphan*/  buildnumber; } ;
struct expr {int dummy; } ;
typedef  enum fill_status { ____Placeholder_fill_status } fill_status ;
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int dwOSVersionInfoSize; int /*<<< orphan*/  wServicePackMinor; int /*<<< orphan*/  wServicePackMajor; scalar_t__* szCSDVersion; } ;
typedef  int /*<<< orphan*/  OSVERSIONINFOW ;
typedef  TYPE_1__ OSVERSIONINFOEXW ;

/* Variables and functions */
 int FILL_STATUS_FAILED ; 
 int FILL_STATUS_UNFILTERED ; 
 int /*<<< orphan*/  GetSystemDefaultLangID () ; 
 int /*<<< orphan*/  GetVersionExW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  free_row_values (struct table*,scalar_t__) ; 
 int get_available_physical_memory () ; 
 int /*<<< orphan*/  get_codeset () ; 
 int /*<<< orphan*/  get_countrycode () ; 
 int /*<<< orphan*/  get_lastbootuptime () ; 
 int /*<<< orphan*/  get_localdatetime () ; 
 int /*<<< orphan*/  get_locale () ; 
 int /*<<< orphan*/  get_osarchitecture () ; 
 int /*<<< orphan*/  get_osbuildnumber (TYPE_1__*) ; 
 int /*<<< orphan*/  get_oscaption (TYPE_1__*) ; 
 int /*<<< orphan*/  get_osname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_osversion (TYPE_1__*) ; 
 int /*<<< orphan*/  get_systemdirectory () ; 
 int get_total_physical_memory () ; 
 int /*<<< orphan*/ * heap_strdupW (scalar_t__*) ; 
 int /*<<< orphan*/  match_row (struct table*,scalar_t__,struct expr const*,int*) ; 
 int /*<<< orphan*/  os_installdateW ; 
 int /*<<< orphan*/  os_serialnumberW ; 
 int /*<<< orphan*/  resize_table (struct table*,int,int) ; 

__attribute__((used)) static enum fill_status fill_os( struct table *table, const struct expr *cond )
{
    struct record_operatingsystem *rec;
    enum fill_status status = FILL_STATUS_UNFILTERED;
    OSVERSIONINFOEXW ver;
    UINT row = 0;

    if (!resize_table( table, 1, sizeof(*rec) )) return FILL_STATUS_FAILED;

    ver.dwOSVersionInfoSize = sizeof(ver);
    GetVersionExW( (OSVERSIONINFOW *)&ver );

    rec = (struct record_operatingsystem *)table->data;
    rec->buildnumber            = get_osbuildnumber( &ver );
    rec->caption                = get_oscaption( &ver );
    rec->codeset                = get_codeset();
    rec->countrycode            = get_countrycode();
    rec->csdversion             = ver.szCSDVersion[0] ? heap_strdupW( ver.szCSDVersion ) : NULL;
    rec->freephysicalmemory     = get_available_physical_memory() / 1024;
    rec->installdate            = os_installdateW;
    rec->lastbootuptime         = get_lastbootuptime();
    rec->localdatetime          = get_localdatetime();
    rec->locale                 = get_locale();
    rec->name                   = get_osname( rec->caption );
    rec->osarchitecture         = get_osarchitecture();
    rec->oslanguage             = GetSystemDefaultLangID();
    rec->osproductsuite         = 2461140; /* Windows XP Professional  */
    rec->ostype                 = 18;      /* WINNT */
    rec->primary                = -1;
    rec->serialnumber           = os_serialnumberW;
    rec->servicepackmajor       = ver.wServicePackMajor;
    rec->servicepackminor       = ver.wServicePackMinor;
    rec->suitemask              = 272;     /* Single User + Terminal */
    rec->systemdirectory        = get_systemdirectory();
    rec->totalvirtualmemorysize = get_total_physical_memory() / 1024;
    rec->totalvisiblememorysize = rec->totalvirtualmemorysize;
    rec->version                = get_osversion( &ver );
    if (!match_row( table, row, cond, &status )) free_row_values( table, row );
    else row++;

    TRACE("created %u rows\n", row);
    table->num_rows = row;
    return status;
}