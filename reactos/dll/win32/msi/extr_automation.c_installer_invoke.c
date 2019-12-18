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
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  LCID ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  EXCEPINFO ;
typedef  int /*<<< orphan*/  DISPPARAMS ;
typedef  int DISPID ;
typedef  int /*<<< orphan*/  AutomationObject ;

/* Variables and functions */
#define  DISPID_INSTALLER_CREATERECORD 146 
#define  DISPID_INSTALLER_ENABLELOG 145 
#define  DISPID_INSTALLER_ENVIRONMENT 144 
#define  DISPID_INSTALLER_FILEATTRIBUTES 143 
#define  DISPID_INSTALLER_FILESIZE 142 
#define  DISPID_INSTALLER_FILEVERSION 141 
#define  DISPID_INSTALLER_INSTALLPRODUCT 140 
#define  DISPID_INSTALLER_LASTERRORRECORD 139 
#define  DISPID_INSTALLER_OPENDATABASE 138 
#define  DISPID_INSTALLER_OPENPACKAGE 137 
#define  DISPID_INSTALLER_OPENPRODUCT 136 
#define  DISPID_INSTALLER_PRODUCTINFO 135 
#define  DISPID_INSTALLER_PRODUCTS 134 
#define  DISPID_INSTALLER_PRODUCTSTATE 133 
#define  DISPID_INSTALLER_REGISTRYVALUE 132 
#define  DISPID_INSTALLER_RELATEDPRODUCTS 131 
#define  DISPID_INSTALLER_SUMMARYINFORMATION 130 
#define  DISPID_INSTALLER_UILEVEL 129 
#define  DISPID_INSTALLER_VERSION 128 
 int /*<<< orphan*/  DISP_E_MEMBERNOTFOUND ; 
 int /*<<< orphan*/  InstallerImpl_CreateRecord (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstallerImpl_EnableLog (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstallerImpl_Environment (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstallerImpl_FileAttributes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstallerImpl_FileSize (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstallerImpl_FileVersion (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstallerImpl_InstallProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstallerImpl_LastErrorRecord (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstallerImpl_OpenDatabase (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstallerImpl_OpenPackage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstallerImpl_OpenProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstallerImpl_ProductInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstallerImpl_ProductState (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstallerImpl_Products (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstallerImpl_RegistryValue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstallerImpl_RelatedProducts (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstallerImpl_SummaryInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstallerImpl_UILevel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstallerImpl_Version (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT installer_invoke(
        AutomationObject* This,
        DISPID dispIdMember,
        REFIID riid,
        LCID lcid,
        WORD wFlags,
        DISPPARAMS* pDispParams,
        VARIANT* pVarResult,
        EXCEPINFO* pExcepInfo,
        UINT* puArgErr)
{
    switch (dispIdMember)
    {
        case DISPID_INSTALLER_CREATERECORD:
            return InstallerImpl_CreateRecord(wFlags, pDispParams,
                                              pVarResult, pExcepInfo, puArgErr);

        case DISPID_INSTALLER_OPENPACKAGE:
            return InstallerImpl_OpenPackage(This, wFlags, pDispParams,
                                             pVarResult, pExcepInfo, puArgErr);

        case DISPID_INSTALLER_OPENPRODUCT:
            return InstallerImpl_OpenProduct(wFlags, pDispParams,
                                             pVarResult, pExcepInfo, puArgErr);

        case DISPID_INSTALLER_OPENDATABASE:
            return InstallerImpl_OpenDatabase(wFlags, pDispParams,
                                              pVarResult, pExcepInfo, puArgErr);

        case DISPID_INSTALLER_SUMMARYINFORMATION:
            return InstallerImpl_SummaryInformation(wFlags, pDispParams,
                                                    pVarResult, pExcepInfo,
                                                    puArgErr);

        case DISPID_INSTALLER_UILEVEL:
            return InstallerImpl_UILevel(wFlags, pDispParams,
                                         pVarResult, pExcepInfo, puArgErr);

        case DISPID_INSTALLER_ENABLELOG:
            return InstallerImpl_EnableLog(wFlags, pDispParams,
                                           pVarResult, pExcepInfo, puArgErr);

        case DISPID_INSTALLER_INSTALLPRODUCT:
            return InstallerImpl_InstallProduct(wFlags, pDispParams,
                                                pVarResult, pExcepInfo,
                                                puArgErr);

        case DISPID_INSTALLER_VERSION:
            return InstallerImpl_Version(wFlags, pVarResult,
                                         pExcepInfo, puArgErr);

        case DISPID_INSTALLER_LASTERRORRECORD:
            return InstallerImpl_LastErrorRecord(wFlags, pDispParams,
                                                 pVarResult, pExcepInfo,
                                                 puArgErr);

        case DISPID_INSTALLER_REGISTRYVALUE:
            return InstallerImpl_RegistryValue(wFlags, pDispParams,
                                               pVarResult, pExcepInfo,
                                               puArgErr);

        case DISPID_INSTALLER_ENVIRONMENT:
            return InstallerImpl_Environment(wFlags, pDispParams,
                                             pVarResult, pExcepInfo, puArgErr);

        case DISPID_INSTALLER_FILEATTRIBUTES:
            return InstallerImpl_FileAttributes(wFlags, pDispParams,
                                                pVarResult, pExcepInfo,
                                                puArgErr);

        case DISPID_INSTALLER_FILESIZE:
            return InstallerImpl_FileSize(wFlags, pDispParams,
                                          pVarResult, pExcepInfo, puArgErr);

        case DISPID_INSTALLER_FILEVERSION:
            return InstallerImpl_FileVersion(wFlags, pDispParams,
                                             pVarResult, pExcepInfo, puArgErr);

        case DISPID_INSTALLER_PRODUCTSTATE:
            return InstallerImpl_ProductState(wFlags, pDispParams,
                                              pVarResult, pExcepInfo, puArgErr);

        case DISPID_INSTALLER_PRODUCTINFO:
            return InstallerImpl_ProductInfo(wFlags, pDispParams,
                                             pVarResult, pExcepInfo, puArgErr);

        case DISPID_INSTALLER_PRODUCTS:
            return InstallerImpl_Products(wFlags, pDispParams,
                                          pVarResult, pExcepInfo, puArgErr);

        case DISPID_INSTALLER_RELATEDPRODUCTS:
            return InstallerImpl_RelatedProducts(wFlags, pDispParams,
                                                 pVarResult, pExcepInfo,
                                                 puArgErr);

        default:
            return DISP_E_MEMBERNOTFOUND;
    }
}