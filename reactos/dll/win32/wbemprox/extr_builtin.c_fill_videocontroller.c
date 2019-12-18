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
struct table {void* num_rows; scalar_t__ data; } ;
struct record_videocontroller {int availability; int current_bitsperpixel; int current_scanmode; int videoarchitecture; int videomemorytype; void* videoprocessor; void* videomodedescription; int /*<<< orphan*/  status; int /*<<< orphan*/  pnpdevice_id; void* name; int /*<<< orphan*/  installeddriver; int /*<<< orphan*/  driverversion; int /*<<< orphan*/  driverdate; void* device_id; void* description; void* current_verticalres; scalar_t__ current_refreshrate; void* current_horizontalres; void* caption; scalar_t__ config_errorcode; void* adapter_ram; int /*<<< orphan*/  adapter_dactype; } ;
struct expr {int dummy; } ;
typedef  enum fill_status { ____Placeholder_fill_status } fill_status ;
typedef  int /*<<< orphan*/  desc ;
typedef  char WCHAR ;
typedef  int UINT64 ;
typedef  void* UINT ;
struct TYPE_5__ {char* Description; int /*<<< orphan*/  VendorId; void* DedicatedVideoMemory; } ;
typedef  int /*<<< orphan*/  IDXGIFactory ;
typedef  int /*<<< orphan*/  IDXGIAdapter ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DXGI_ADAPTER_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  CreateDXGIFactory (int /*<<< orphan*/ *,void**) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int FILL_STATUS_FAILED ; 
 int FILL_STATUS_UNFILTERED ; 
 int /*<<< orphan*/  IDXGIAdapter_GetDesc (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  IDXGIAdapter_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDXGIFactory_EnumAdapters (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDXGIFactory_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDXGIFactory ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,void*) ; 
 int /*<<< orphan*/  free_row_values (struct table*,void*) ; 
 int get_bits_per_pixel (void**,void**) ; 
 int /*<<< orphan*/  get_installeddriver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_pnpdeviceid (TYPE_1__*) ; 
 void* heap_strdupW (char const*) ; 
 int /*<<< orphan*/  match_row (struct table*,void*,struct expr const*,int*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resize_table (struct table*,int,int) ; 
 int /*<<< orphan*/  videocontroller_dactypeW ; 
 void* videocontroller_deviceidW ; 
 int /*<<< orphan*/  videocontroller_driverdateW ; 
 int /*<<< orphan*/  videocontroller_driverversionW ; 
 int /*<<< orphan*/  videocontroller_statusW ; 
 int /*<<< orphan*/  wsprintfW (char*,char const*,void*,void*,int) ; 

__attribute__((used)) static enum fill_status fill_videocontroller( struct table *table, const struct expr *cond )
{
    static const WCHAR fmtW[] = {'%','u',' ','x',' ','%','u',' ','x',' ','%','I','6','4','u',' ','c','o','l','o','r','s',0};
    struct record_videocontroller *rec;
    HRESULT hr;
    IDXGIFactory *factory = NULL;
    IDXGIAdapter *adapter = NULL;
    DXGI_ADAPTER_DESC desc;
    UINT row = 0, hres = 1024, vres = 768, vidmem = 512 * 1024 * 1024;
    const WCHAR *name = videocontroller_deviceidW;
    enum fill_status status = FILL_STATUS_UNFILTERED;
    WCHAR mode[44];

    if (!resize_table( table, 1, sizeof(*rec) )) return FILL_STATUS_FAILED;

    memset (&desc, 0, sizeof(desc));
    hr = CreateDXGIFactory( &IID_IDXGIFactory, (void **)&factory );
    if (FAILED(hr)) goto done;

    hr = IDXGIFactory_EnumAdapters( factory, 0, &adapter );
    if (FAILED(hr)) goto done;

    hr = IDXGIAdapter_GetDesc( adapter, &desc );
    if (SUCCEEDED(hr))
    {
        vidmem = desc.DedicatedVideoMemory;
        name   = desc.Description;
    }

done:
    rec = (struct record_videocontroller *)table->data;
    rec->adapter_dactype       = videocontroller_dactypeW;
    rec->adapter_ram           = vidmem;
    rec->availability          = 3; /* Running or Full Power */
    rec->config_errorcode      = 0; /* no error */
    rec->caption               = heap_strdupW( name );
    rec->current_bitsperpixel  = get_bits_per_pixel( &hres, &vres );
    rec->current_horizontalres = hres;
    rec->current_refreshrate   = 0; /* default refresh rate */
    rec->current_scanmode      = 2; /* Unknown */
    rec->current_verticalres   = vres;
    rec->description           = heap_strdupW( name );
    rec->device_id             = videocontroller_deviceidW;
    rec->driverdate            = videocontroller_driverdateW;
    rec->driverversion         = videocontroller_driverversionW;
    rec->installeddriver       = get_installeddriver( desc.VendorId );
    rec->name                  = heap_strdupW( name );
    rec->pnpdevice_id          = get_pnpdeviceid( &desc );
    rec->status                = videocontroller_statusW;
    rec->videoarchitecture     = 2; /* Unknown */
    rec->videomemorytype       = 2; /* Unknown */
    wsprintfW( mode, fmtW, hres, vres, (UINT64)1 << rec->current_bitsperpixel );
    rec->videomodedescription  = heap_strdupW( mode );
    rec->videoprocessor        = heap_strdupW( name );
    if (!match_row( table, row, cond, &status )) free_row_values( table, row );
    else row++;

    TRACE("created %u rows\n", row);
    table->num_rows = row;

    if (adapter) IDXGIAdapter_Release( adapter );
    if (factory) IDXGIFactory_Release( factory );
    return status;
}