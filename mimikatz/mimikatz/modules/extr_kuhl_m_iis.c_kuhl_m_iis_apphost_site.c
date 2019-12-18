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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  int /*<<< orphan*/  IXMLDOMNodeList ;
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  int /*<<< orphan*/  DOMNodeType ;

/* Variables and functions */
 scalar_t__ IXMLDOMNodeList_get_item (int /*<<< orphan*/ *,long,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLDOMNodeList_get_length (int /*<<< orphan*/ *,long*) ; 
 int /*<<< orphan*/  IXMLDOMNode_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNode_get_nodeType (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNode_selectNodes (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NODE_ELEMENT ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_iis_maybeEncrypted (int,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_xml_getAttribute (int /*<<< orphan*/ *,char*) ; 

void kuhl_m_iis_apphost_site(int argc, wchar_t * argv[], IXMLDOMDocument *pXMLDom, IXMLDOMNode *pNode)
{
	PWSTR gen;
	IXMLDOMNodeList *pAppNodes, *pVdirNodes;
	IXMLDOMNode *pAppNode, *pVdirNode;
	DOMNodeType type;
	long lengthApp, lengthVdir, i, j;

	if(gen = kull_m_xml_getAttribute(pNode, L"name"))
	{
		kprintf(L"\n* Site: \'%s\'\n", gen);
		LocalFree(gen);
		if((IXMLDOMNode_selectNodes(pNode, L"application", &pAppNodes) == S_OK) && pAppNodes)
		{
			if(IXMLDOMNodeList_get_length(pAppNodes, &lengthApp) == S_OK)
			{
				for(i = 0; i < lengthApp; i++)
				{
					if((IXMLDOMNodeList_get_item(pAppNodes, i, &pAppNode) == S_OK) && pAppNode)
					{
						if((IXMLDOMNode_get_nodeType(pAppNode, &type) == S_OK) && (type == NODE_ELEMENT))
						{
							if(gen = kull_m_xml_getAttribute(pAppNode, L"path"))
							{
								kprintf(L"  > Application Path: %s\n", gen);
								LocalFree(gen);
								
								if((IXMLDOMNode_selectNodes(pAppNode, L"virtualDirectory", &pVdirNodes) == S_OK) && pVdirNodes)
								{
									if(IXMLDOMNodeList_get_length(pVdirNodes, &lengthVdir) == S_OK)
									{
										for(j = 0; j < lengthVdir; j++)
										{
											if((IXMLDOMNodeList_get_item(pVdirNodes, j, &pVdirNode) == S_OK) && pVdirNode)
											{
												if((IXMLDOMNode_get_nodeType(pVdirNode, &type) == S_OK) && (type == NODE_ELEMENT))
												{
													if(gen = kull_m_xml_getAttribute(pVdirNode, L"path"))
													{
														kprintf(L"    - VirtualDirectory Path: %s ( ", gen);
														LocalFree(gen);

														if(gen = kull_m_xml_getAttribute(pVdirNode, L"physicalPath"))
														{
															kprintf(L"%s", gen);
															LocalFree(gen);
														}
														kprintf(L" )\n");

														if(gen = kull_m_xml_getAttribute(pVdirNode, L"userName"))
														{
															kprintf(L"      Username: %s\n", gen);
															LocalFree(gen);
															if(gen = kull_m_xml_getAttribute(pVdirNode, L"password"))
															{
																kprintf(L"      Password: %s\n", gen);
																kuhl_m_iis_maybeEncrypted(argc, argv, pXMLDom, gen);
																LocalFree(gen);
															}
														}
													}
												}
												IXMLDOMNode_Release(pVdirNode);
											}
										}
									}
								}
							}
						}
						IXMLDOMNode_Release(pAppNode);
					}
				}
			}
		}
	}
}